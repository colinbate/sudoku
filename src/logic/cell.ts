import type { Gridlike, Possibilities } from "./types";


export const ALL_POSSIBLE: Possibilities = [null, true, true, true, true, true, true, true, true, true];
export const NO_POSSIBLE: Possibilities = [null, false, false, false, false, false, false, false, false, false];

export class Cell {
  original = false;
  private possible: Possibilities;
  private grid: Gridlike;

  constructor(private value: number) {
    if (value >= 0 && value <= 9) {
			if (value === 0) {
				this.possible = [...ALL_POSSIBLE];
			} else {
        this.original = true;
				this.possible = [...NO_POSSIBLE];
			}
		}
  }

  setGrid(grid: Gridlike) {
    this.grid = grid;
  }

  setValue(value: number) {
    if (value >= 1 && value <= 9 && this.value === 0) {
			this.value = value;
			this.possible = [...NO_POSSIBLE];
			this.grid.foundOne();
		}
  }

  isKnown() {
    return this.value !== 0;
  }

  getValue() {
    return this.value;
  }

  couldBe(value: number) {
    return this.possible[value];
  }

  cantBe(value: number) {
    this.possible[value] = false;
    this.check();
  }

  notPossible(others: Possibilities) {
    if (this.value !== 0) {
      return;
    }
    for (let i = 1; i <= 9; i++) {
      if (others[i]) {
        this.possible[i] = false
      }
    }
    this.check();
  }

  toString() {
    return this.value === 0 ? '.' : this.value.toString();
  }

  private check() {
    if (this.value !== 0) {
      return;
    }
		let pcount = 0;
		let found = 0;
		for (let i = 1; i <= 9; i++) {
			if (this.possible[i]) {
				pcount++;
				found = i;
			}
		}
		if (pcount === 1) {
			this.setValue(found);
		}
  }
}