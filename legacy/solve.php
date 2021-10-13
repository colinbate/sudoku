<?php
require_once('echo.inc');
require_once('Grid.inc');
$page = new ePage();
$page->title("su doku");
$page->content_start();

$raw_grid = $_POST['raw_grid'];
$sudoku = new Grid($raw_grid);
$sudoku->solve();
$solved = trim($sudoku->toString());
$lines = explode("\n", $solved);
?>
<h1>Su Doku Solver <span class="beta">Beta</span></h1>

<table class="sudoku" cellspacing="0">
<?php
$lc = 0;
foreach ($lines as $line) {
	if ($lc == 2 || $lc == 5) {
		$h = 'majorh';
	} else {
		$h = '';
	}
	echo "<tr>\n";
	for ($i=0; $i<9; $i++) {
		$v = '';
		if ($i == 2 || $i == 5) {
			$v = 'majorv';
		}
		$class = trim("$v $h");
		if ($class != '') $class = " class=\"$class\"";
		echo "<td$class>" . $line{$i} . "</td>\n";
	}
	echo "</tr>\n";
	$lc++;
}
?>
</table>

<?php
$page->content_end();
$page->render();
?>