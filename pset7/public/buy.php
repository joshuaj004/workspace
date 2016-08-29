<?php

    // configuration
    require("../includes/config.php"); 
    
    if ($_SERVER["REQUEST_METHOD"] == "GET") {
        // else render form
        render("buy_form.php");
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $user_stock = strtoupper($_POST["symbol"]);
        $stock = lookup($user_stock);
        if ($stock === false) {
            apologize("We could not find that symbol. Please make sure you entered it in correctly.");
        }
        
        if (!preg_match("/^\d+$/", $_POST["shares"])) {
            apologize("Please enter a whole, positive number.");
        }
        $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $id = $_SESSION["id"];
        $shares = $_POST["shares"];
        $cost = $shares * $stock["price"];
        if ($cash[0]["cash"] < $cost) {
            apologize("You do not have enough funds to purchase that amount of stocks right now.");
        }
        
        $transaction = "BUY";
        date_default_timezone_set('America/Los_Angeles');
        $date = date("Y-m-d H:i:s"); 
        $symbol = $_POST["symbol"];
        //$shares = $number[0]["shares"];
        $price = $stock["price"];
        //$id = $_SESSION["id"];
        CS50::query("INSERT INTO history (`user_id`, `transaction`, `shares`, `price`, `date`, `symbol`) VALUES ('$id', '$transaction', '$shares', '$price', '$date', '$symbol')");
        CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES('$id', '$user_stock', '$shares') ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)");  
        CS50::query("UPDATE users SET cash = cash - '$cost' WHERE id = '$id'");
        //
        redirect("/");
        /*
        render("quote_form.php", ["symbol" => $stock["symbol"], "name" => $stock["name"], "price" => $stock["price"]]);
        */
    }
?>