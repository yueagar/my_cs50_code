from cs50 import SQL

db = SQL("sqlite:///favorites.db")

favorite = input("Favorite: ")

#rows = db.execute(f"SELECT * AS n FROM favorites WHERE problem = '{favorite}'")
rows = db.execute(f"SELECT COUNT(*) AS n FROM favorites WHERE problem = '{favorite}'")

#for row in rows:
    #print(row["Timestamp"])
print(rows[0]["n"])