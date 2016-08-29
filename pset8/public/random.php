<?php
    require(__DIR__ . "/../includes/config.php");
    
    $random_loc = CS50::query("SELECT * FROM places ORDER BY RAND() LIMIT 1");
    header("Content-type: application/json");
    print(json_encode($random_loc, JSON_PRETTY_PRINT));

?>