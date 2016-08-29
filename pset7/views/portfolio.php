<?php /*<div>
    <iframe allowfullscreen frameborder="0" height="315" src="https://www.youtube.com/embed/oHg5SJYRHA0?autoplay=1&iv_load_policy=3&rel=0" width="420"></iframe>
</div>*/?>
<?php //<p>Cash: $ $cash  </p> ?>
<table class="table table-striped">
    <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>TOTAL</th>
        </tr>
    </thead>
    <tbody></tbody>
    <tr>
        <td colspan="4">CASH</td>    
        <td>$<?= number_format($cash, 2) ?></td>
    </tr>
    
    <?php foreach ($positions as $position): ?>
    
    <tr>
        <td><?= $position["symbol"] ?></td>
        <td><?= $position["name"] ?></td>
        <td><?= $position["shares"] ?></td>
        <td><?= "$" . number_format($position["price"], 2) ?></td>
        <?php $total = ($position["shares"] * $position["price"]);?>
        <td><?= "$" . number_format($total, 2) ?></td>
    </tr>
    <?php endforeach ?>
    </tbody>
</table>