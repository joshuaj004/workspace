<form action="quote.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="symbol" placeholder="Symbol" type="text"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Look up
            </button>
        </div>
    </fieldset>
</form>
<?php if (!empty($price)) { ?>
    <p><?= "Name: " . $name ?></p>
    <p><?= "Symbol: " . $symbol ?></p>
    <p><?= "Price: " . number_format($price, 2) ?></p>
<?php } ?>
