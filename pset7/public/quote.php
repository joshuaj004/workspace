<?php

    // configuration
    require("../includes/config.php"); 
    
    if ($_SERVER["REQUEST_METHOD"] == "GET") {
        // else render form
        render("quote_form.php");
    } 
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = lookup($_POST["symbol"]);
        
        if ($stock === false) {
            apologize("We could not find that symbol. Please make sure you entered it in correctly.");
        }
        
        render("quote_form.php", ["symbol" => $stock["symbol"], "name" => $stock["name"], "price" => $stock["price"]]);
    }
?>