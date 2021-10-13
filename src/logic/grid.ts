import { Cell } from "./cell";
import { Section } from "./section";
import { BoxType, ColType, RowType, UiCell } from './types';

export class Grid {
  known: number = 0;
  private rows: Section[] = [];
  private cols: Section[] = [];
  private boxes: Section[] = [];
  private cells: Cell[] = [];

  constructor(grid: string) {
    for (let i = 1; i <= 9; i++) {
      this.rows[i] = new Section(RowType);
      this.cols[i] = new Section(ColType);
      this.boxes[i] = new Section(BoxType);
    }
    this.parse(grid);
  }

  foundOne() {
    this.known += 1;
  }

  isSolved() {
    return this.known === 81;
  }

  eliminate() {
    for (let r = 1; r <= 9; r += 1) {
      this.rows[r].removeUsed();
      this.cols[r].removeUsed();
      this.boxes[r].removeUsed();
      this.rows[r].singleChoice();
      this.cols[r].singleChoice();
      this.boxes[r].singleChoice();
    }
  }

  solve() {
    let tries = 1;
    while (!this.isSolved() && tries <= 32) {
      this.eliminate();
      tries += 1;
    }
  }

  toString() {
    const r: string[] = [];
    for (let i = 1; i <= 9; i += 1) {
      r.push(this.rows[i].toString());
    }
    return r.join('');
  }

  toData() {
    const d: (UiCell | '')[][] = [];
    for (let r = 1; r <= 9; r += 1) {
      d.push(this.rows[r].toData());
    }
    return d;
  }

  private boxNum(x: number, y: number) {
    const cx = Math.ceil(x/3.0);
    const cy = Math.ceil(y/3.0);
    return (cy - 1) * 3 + cx;
  }

  private numberInBox(x: number, y: number) {
    let mx = x % 3;
    if (mx === 0) {
      mx = 3;
    }
    let my = y % 3;
    if (my === 0) {
      my = 3;
    }
    return (my - 1) * 3 + mx;
  }

  private parse(rawGrid: string) {
    const gstring = rawGrid.replace(/[\n\r]/g, '');
    for (let y = 1; y <= 9; y += 1) {
      for (let x = 1; x <= 9; x += 1) {
        const ind = (y - 1) * 9 + (x - 1);
        const cellStr = gstring[ind];
        const b = this.boxNum(x, y);
        const numinbox = this.numberInBox(x, y);
        let cellValue: number;
        if (cellStr === '.') {
          cellValue = 0;
        } else {
          cellValue = parseInt(cellStr, 10);
          this.known += 1;
        }
        //console.log('r', y, 'c', x, 'b', b, 'v', cellValue);
        const c = new Cell(cellValue);
        this.cells[ind] = c;
        this.cells[ind].setGrid(this);
        this.rows[y].addCell(c, x);
        this.cols[x].addCell(c, y);
        this.boxes[b].addCell(c, numinbox);
      }
    }
  }

}