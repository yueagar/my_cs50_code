class App {
    constructor() {
        const pageRegex = window.location.pathname.match(/\/([a-z]+)\.html/);
        this.page = pageRegex ? pageRegex[1] : "index";
    };
    init() {
        console.log(`Preparing ${this.page}.`);
        switch (this.page) {
            case "index":
                this.prepareIndex();
                break;
            case "about":
                this.prepareAbout();
                break;
            case "experience":
                this.prepareExperience();
                break;
            case "contact":
                this.prepareContact();
                break;
            default:
                console.log("Preparation failed.");
                break;
        };
    };
    prepareIndex() {
        const opening = document.querySelector("#opening");
        let text = "";
        let counter = 0;
        let string = `int main()\n{\n　　printf("Hello, world!");\n　　return 0;\n}\n\n> gcc -o hello.exe hello.c\n> ./hello`;
        const showText = setInterval(() => {
            text += string[counter];
            opening.innerText = text;
            counter++;
            if (counter >= string.length) {
                opening.style.opacity = 0;
                setTimeout(() => {
                    opening.style.zIndex = 0;
                }, 3000);
                clearInterval(showText);
            };
        }, 50);
    };
    prepareAbout() {
        // here goes nothing...
    };
    prepareExperience() {
        // here goes nothing...
    };
    prepareContact() {
        // here goes nothing...
    };
};

document.addEventListener("DOMContentLoaded", () => {
    const HomepageApp = new App();
    window.HomepageApp = HomepageApp;
    HomepageApp.init();
});