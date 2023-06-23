import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    total = 0
    stocks = []
    items = []

    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)
    for transaction in transactions:
        transaction["price"] = lookup(transaction["symbol"])["price"]
        total += transaction["shares"] * transaction["price"]
        if transaction["symbol"] in stocks:
            item = items[stocks.index(transaction["symbol"])]
            item["shares"] += transaction["shares"]
            item["total"] = usd(item["shares"] * transaction["price"])
        else:
            stocks.append(transaction["symbol"])
            items.append({
                "symbol": transaction["symbol"],
                "name": transaction["symbol"],
                "shares": transaction["shares"],
                "price": usd(transaction["price"]),
                "total": usd(transaction["shares"] * transaction["price"])
            })

    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    total += cash

    return render_template("index.html", items=items, cash=usd(cash), total=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("missing symbol")
        elif not shares:
            return apology("missing shares")

        try:
            shares = int(shares)
        except ValueError:
            return apology("invalid shares")

        if shares < 1:
            return apology("invalid shares")

        stock = lookup(symbol)

        if not stock:
            return apology("invalid symbol")

        user_id = session["user_id"]

        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        if stock['price'] * shares > cash:
           return apology("can't afford")

        cash -= stock["price"] * shares

        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, user_id)
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)", user_id, symbol, shares, stock["price"])

        flash("Bought!")

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]

    items = []

    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)
    for transaction in transactions:
        items.append({
            "symbol": transaction["symbol"],
            "shares": transaction["shares"],
            "price": usd(transaction["price"]),
            "time": transaction["time"]
        })

    return render_template("history.html", transactions=items)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("missing symbol")

        result = lookup(symbol)

        if not result:
            return apology("invalid symbol")

        result["price"] = usd(result["price"])

        return render_template("quoted.html", result=result)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username")
        elif not password:
            return apology("must provide password")
        elif len(db.execute("SELECT * FROM users WHERE username = ?", username)) > 0:
            return apology("username is not available")
        elif password != confirmation:
            return apology("passwords don't match")

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))

        session["user_id"] = db.execute("SELECT * FROM users WHERE username = ?", username)[0]['id']

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    owned_stocks = []
    owned_stocks_list = []

    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)
    for transaction in transactions:
        if transaction["symbol"] not in owned_stocks_list and transaction["shares"] > 0:
            owned_stocks_list.append(transaction["symbol"])
            owned_stocks.append({
                "symbol": transaction["symbol"],
                "shares": transaction["shares"]
            })
        elif transaction["shares"] > 0:
            item = owned_stocks[owned_stocks_list.index(transaction["symbol"])]
            item["shares"] += transaction["shares"]

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("missing symbol")
        elif not shares:
            return apology("missing shares")

        try:
            shares = int(shares)
        except ValueError:
            return apology("invalid shares")

        if shares < 1:
            return apology("invalid shares")

        stock = lookup(symbol)

        if not stock:
            return apology("invalid symbol")
        elif symbol not in owned_stocks_list:
            return apology("symbol not owned")

        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        if shares > owned_stocks[owned_stocks_list.index(symbol)]["shares"]:
           return apology("too many shares")

        cash += stock["price"] * shares

        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, user_id)
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)", user_id, symbol, -shares, stock["price"])

        flash("Sold!")

        return redirect("/")

    else:
        return render_template("sell.html", stocks=owned_stocks_list)


@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Sell shares of stock"""

    if request.method == "POST":

        amount = request.form.get("amount")

        try:
            amount = float(amount)
        except ValueError:
            return apology("invalid amount")

        if amount < 0:
            return apology("invalid amount")

        user_id = session["user_id"]

        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        cash += amount

        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, user_id)

        flash(f"Added {usd(amount)}")

        return redirect("/")

    else:
        return render_template("add_cash.html")


@app.route("/changepw", methods=["GET", "POST"])
@login_required
def changepw():
    """Sell shares of stock"""

    if request.method == "POST":
        user_id = session["user_id"]

        old_pw = request.form.get("old_password")
        new_pw = request.form.get("new_password")
        con_pw = request.form.get("confirmation")

        if new_pw != con_pw:
            return apology("passwords don't match")

        cur_pw = db.execute("SELECT hash FROM users WHERE id = ?", user_id)[0]["hash"]

        if not check_password_hash(cur_pw, old_pw):
            return apology("invalid password")

        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(new_pw), user_id)

        flash("Password changed!")

        return redirect("/")

    else:
        return render_template("changepw.html")