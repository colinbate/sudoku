<?php
require_once('Section.inc');

/**
 *
 *
 */
class Grid {
	var $rows;
	var $cols;
	var $boxes;
	var $cells;
	
	var $known;
	
	function Grid($raw_grid) {
		$this->known = 0;
		$this->_create_sections();
		$this->_parse_grid($raw_grid);
	}
	
	function _create_sections() {
		for ($i = 1; $i <= 9; $i++) {
			$this->rows[$i] = new Section(SUDOKU_SECTION_ROW, $i); 
			$this->cols[$i] = new Section(SUDOKU_SECTION_COL, $i);
			$this->boxes[$i] = new Section(SUDOKU_SECTION_BOX, $i);
		}
	}
	
	function _parse_grid($raw_grid) {
		$gstring = str_replace("\n", '', $raw_grid);
		$gstring = str_replace("\r", '', $gstring);
		$ind = 0;
		for ($y = 1; $y <= 9; $y++) {
			for ($x = 1; $x <= 9; $x++) {
				$ind = ($y-1) * 9 + ($x-1);
				$cell_num = $gstring{$ind};
				$b = $this->_box_num($x, $y);
				$numinbox = $this->_num_in_box($x, $y);
				//debug("r$y:c$x:b$b:v$cell_num |");
				if ($cell_num == '.') {
					$cell_num = 0;
				} else {
					$this->known++;
				}
				$cells[$ind] = new Cell($this->rows[$y], $this->cols[$x], $this->boxes[$b], $cell_num);
				$cells[$ind]->setGrid(&$this);
				$newcell =& $cells[$ind];
				$this->rows[$y]->addCell(&$newcell, $x);
				$this->cols[$x]->addCell(&$newcell, $y);
				$this->boxes[$b]->addCell(&$newcell, $numinbox);
			}
			//debug("\n");
		}
	}
	
	function foundOne() {
		$this->known++;
	}
	
	function _box_num($x, $y) {
		$cx = ceil($x/3.0);
		$cy = ceil($y/3.0);
		return ($cy-1)*3 + $cx;
	}
	
	function _num_in_box($x, $y) {
		$mx = $x % 3;
		if ($mx == 0) $mx = 3;
		$my = $y % 3;
		if ($my == 0) $my = 3;
		return ($my-1)*3 + $mx;
	}
	
	function eliminate() {
		for ($r = 1; $r <= 9; $r++) {
			$this->rows[$r]->removeUsed();
			$this->cols[$r]->removeUsed();
			$this->boxes[$r]->removeUsed();
			$this->rows[$r]->singleChoice();
			$this->cols[$r]->singleChoice();
			$this->boxes[$r]->singleChoice();
		}
	}
	
	function solve() {
		$tries = 1;
		while (!$this->isSolved() && $tries <= 12) {
			$this->eliminate();
			$tries++;
		}
	}
	
	function isSolved() {
		return ($this->known == 81);
	}
	
	function toString($debug = 0) {
		$crow = null;
		$r = '';
		for ($i = 1; $i <= 9; $i++) {
			$crow = $this->rows[$i];
			$r .= $crow->toString($debug);
		}
		return $r;
	}
}
?>