<?php

    // configuration
    require("../includes/config.php"); 
    
    //$rows = CS50::query("SELECT symbol FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    $rows = CS50::query("SELECT * FROM history WHERE user_id = ?", $_SESSION["id"]);
    
    render("history_form.php", ["rows" => $rows]);
?>