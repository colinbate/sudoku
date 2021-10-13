import { Cell, NO_POSSIBLE } from "./cell";
import { ColType, Possibilities, RowType, SectionType, UiCell } from "./types";


export class Section {
  contents: Cell[];
  ccount: number;
  constructor(private type: SectionType) {
    this.contents = [];
    this.ccount = 0;
  }

  addCell(cell: Cell, pos: number) {
    this.contents[pos] = cell;
    this.ccount += 1;
  }

  getUsedValues() {
    const vals: Possibilities = [...NO_POSSIBLE];
    for (let i = 1; i <= 9; i += 1) {
      if (this.contents[i].isKnown()) {
        const known = this.contents[i].getValue();
        vals[known] = true;
      }
    }
    return vals;
  }

  removeUsed() {
    const used = this.getUsedValues();
    for (let i = 1; i <= 9; i += 1) {
      this.contents[i].notPossible(used);
    }
  }

  singleChoice() {
    for (let i = 1; i <= 9; i += 1) {
      let vposs = 0;
      let vcount = 0;
      let j = 1;
      let used = false;
      while (j <= 9 && !used) {
        if (this.contents[j].getValue() === i) {
          used = true;
        } else if (this.contents[j].couldBe(i)) {
          vcount += 1;
          vposs = j;
        }
        j += 1;
      }
      if (used) {
        continue;
      }
      if (vcount === 1) {
        this.contents[vposs].setValue(i);
      }
    }
  }

  isFull() {
    let full = true;
    for (let i = 1; i <= 9; i += 1) {
      if (!this.contents[i].isKnown()) {
        full = false;
        break;
      }
    }
    return full;
  }

  toString() {
    const r: string[] = [];
    let cell: Cell;
    if (this.ccount < 9) {
      return '';
    }
    for (let i = 1; i <= 9; i += 1) {
      cell = this.contents[i];
      if (this.type === RowType) {
        r.push(cell.toString());
        if (i === 9) {
          r.push('\n');
        }
      } else if (this.type === ColType) {
        r.push(cell.toString());
        r.push('\n');
      } else {
        r.push(cell.toString());
        if (i === 3 || i === 6 || i === 9) {
          r.push('\n');
        }
      }
    }
    return r.join('');
  }

  toData() {
    const s: (UiCell | '')[] = this.contents
      .filter(c => !!c)
      .map(c => (c.isKnown ? {type: c.original ? 'b' : '', num: c.getValue()} : ''));
    return s;
  }
}