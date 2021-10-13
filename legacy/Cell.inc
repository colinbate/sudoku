<?php
/**
 *
 *
 */
class Cell {
	var $possible;
	var $value;
	
	var $row;
	var $col;
	var $box;
	
	var $grid;
	
	var $x;
	var $y;
	
	function Cell($row, $col, $box, $value = 0) {
		if ($value >= 0 && $value <= 9) {
			if ($value == 0) {
				$this->possible = array_fill(1, 9, 1);
			} else {
				$this->possible = array_fill(1, 9, 0);
			}
			$this->value = $value;
			
			$this->row = $row;
			$this->col = $col;
			$this->box = $box;
		}
	}
	
	function setGrid(&$grid) {
		$this->grid =& $grid;
	}
	
	function setValue($value) {
		if ($value >= 1 && $value <= 9 && $this->value == 0) {
			$this->value = $value;
			$this->possible = array_fill(1, 9, 0);
			$this->grid->foundOne();
		}
	}
	
	function isKnown() {
		return ($this->value != 0);
	}
	
	function getValue() {
		return $this->value;
	}
	
	function couldBe($value) {
		return ($this->possible[$value] == 1);
	}
	
	function cantBe($value) {
		$this->possible[$value] = 0;
		$this->_eval();
	}
	
	function notPossible($array_values) {
		if ($this->value != 0) return;
		for ($i = 1; $i <= 9; $i++) {
			if ($array_values[$i] == 1) {
				$this->possible[$i] = 0;
			}
		}
		$this->_eval();
	}
	
	function _eval() {
		if ($this->value != 0) return;
		$pcount = 0;
		$found = 0;
		for ($i = 1; $i <= 9; $i++) {
			if ($this->possible[$i] == 1) {
				$pcount++;
				$found = $i;
			}
		}
		if ($pcount == 1) {
			$this->setValue($found);
		}
	}
	
	function toString($debug = 0) {
		if ($debug == 0) {
			if ($this->value == 0) {
				return '.';
			} else {
				return '' . $this->value;
			}
		} else {
			$r = '';
			for ($i = 1; $i <= 9; $i++) {
				if ($this->possible[$i] == 1) {
					$r .= $i;
				} else {
					$r .= '.';
				}
			}
			
			return $r . ':' . $this->value . ' |';
		}
	}
}
?>