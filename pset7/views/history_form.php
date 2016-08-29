<table class="table table-striped">

    <thead>
        <tr>
            <th>Transaction</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>

    <tbody>
    <?php foreach ($rows as $row): ?>
    <tr>
        <td><?= $row["transaction"] ?></td>
        <?php 
        $time = strtotime($row["date"]);
        $myFormatForView = date("m/d/y g:i A", $time); ?>
        <td><?= $myFormatForView ?></td>
        <td><?= $row["symbol"] ?></td>
        <td><?= $row["shares"] ?></td>
        <td><?= "$" . number_format($row["price"], 2) ?></td>
    </tr>
    <?php endforeach ?>
    </tbody>

</table>