<?php 

    // configuration
    require("../includes/config.php"); 
    
     // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        $rows = CS50::query("SELECT symbol FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
        //array_unshift($rows, "Symbol");
        //print_r($rows);
        render("sell_form.php", ["title" => "Sell", "rows" => $rows]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //var_dump($_POST);
        //print_r($symbol);
        $stock = lookup($_POST["symbol"]);
        //print_r($stock["price"]);
        $number = CS50::query("SELECT shares FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $stock["symbol"]);
        //print_r($number);
        //print_r($number[0]["shares"]);
        $money = $number[0]["shares"] * $stock["price"];
        //print_r($money);
        $transaction = "SELL";
        date_default_timezone_set('America/Los_Angeles');
        $date = date("Y-m-d H:i:s"); 
        $symbol = $_POST["symbol"];
        $shares = $number[0]["shares"];
        $price = $stock["price"];
        $id = $_SESSION["id"];
        CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $stock["symbol"]);
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $money, $_SESSION["id"]);
        CS50::query("INSERT INTO history (`user_id`, `transaction`, `shares`, `price`, `date`, `symbol`) VALUES ('$id', '$transaction', '$shares', '$price', '$date', '$symbol')");
        redirect("/");
    }

?>