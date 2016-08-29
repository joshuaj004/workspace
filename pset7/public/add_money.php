<?php
    // configuration
    require("../includes/config.php"); 
    
    $id = $_SESSION["id"];
    CS50::query("UPDATE users SET cash = cash + 1000 WHERE id = '$id'");
    redirect("/buy.php");
?>