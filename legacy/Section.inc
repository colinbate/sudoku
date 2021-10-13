<?php
require_once('Cell.inc');

define('SUDOKU_SECTION_ROW', 1);
define('SUDOKU_SECTION_COL', 2);
define('SUDOKU_SECTION_BOX', 3);

/**
 *
 *
 */
class Section {
	var $type;
	var $contents;
	var $position;
	var $ccount;
	
	function Section($type, $position) {
		$this->type = $type;
		$this->position = $position;
		$this->contents = array_fill(1, 9, 0);
		$this->ccount = 0;
	}
	
	function addCell(&$cell, $pos) {
		$this->contents[$pos] =& $cell;
		$this->ccount++;
	}
	
	/**
	 * Retrieves the list of which values are already present in a section.
	 *
	 * @return array
	 */
	function getUsedValues() {
		$rar = array_fill(1, 9, 0);
		for ($i = 1; $i <= 9; $i++) {
			if ($this->contents[$i]->isKnown()) {
				$kval = $this->contents[$i]->getValue();
				$rar[$kval] = 1;
			}
		}
		return $rar;
	}
	
	/**
	 * This removes from each cell in the section the option of
	 * using another value already used in the section.
	 *
	 *
	 */
	function removeUsed() {
		$used = $this->getUsedValues();
		for ($i = 1; $i <= 9; $i++) {
			$this->contents[$i]->notPossible($used);
		}
	}
	
	/**
	 * Scans each value to see if there is only one cell
	 * in the section that could be that value.
	 */
	function singleChoice() {
		for ($val = 1; $val <= 9; $val++) {
			$vposs = 0;
			$vcount = 0;
			$i = 1;
			$used = false;
			while ($i <= 9 && !$used) {
				if ($this->contents[$i]->getValue() == $val) {
					$used = true;
				} else if ($this->contents[$i]->couldBe($val)) {
					$vcount++;
					$vposs = $i;
				}
				$i++;
			}
			if ($used) continue;
			if ($vcount == 1) {
				$this->contents[$vposs]->setValue($val);
			}
		}
	}
	
	function isFull() {
		$full = true;
		for ($i = 1; $i <= 9; $i++) {
			$cell = $this->contents[$i];
			if (!$cell->isKnown()) $full = false;
		}
		return $full;
	}
	
	function toString($debug = 0) {
		$r = '';
		$cell = null;
		if ($this->ccount < 9) return '';
		for ($i = 1; $i <= 9; $i++) {
			$cell = $this->contents[$i];
			if ($this->type == SUDOKU_SECTION_ROW) {
				$r .= $cell->toString($debug);
				if ($i == 9) $r .= "\n";
			} elseif ($this->type == SUDOKU_SECTION_COL) {
				$r .= $cell->toString($debug) . "\n";
			} else {
				$r .= $cell->toString($debug);
				if ($i == 3 || $i == 6 || $i == 9) {
					$r .= "\n";
				}
			}
		}
		return $r;
	}
	
	
}
?>