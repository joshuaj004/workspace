<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["username"])) {
            apologize("You must provide your username.");
        }
        if (empty($_POST["password"])) {
            apologize("You need a passowrd");
        }
        
        if (empty($_POST["confirmation"])) {
            apologize("You need to confirm your password");
        }
        
        if ($_POST["password"] !== $_POST["confirmation"]) {
            apologize("Your password and confirmation do not match");
        }
        
        $success = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
        if ($success === 0) {
            apologize("That username has already been used");
        }
        
        $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
        $id = $rows[0]["id"];
        $_SESSION["id"] = $id;
        
        redirect("/");

    }

?>
