export interface Gridlike {
  foundOne: () => void
}

export type Possibilities = [null, boolean, boolean, boolean, boolean, boolean, boolean, boolean, boolean, boolean];

export const RowType = 1;
export const ColType = 2;
export const BoxType = 3;
export type SectionType = typeof RowType | typeof ColType | typeof BoxType;

export interface UiCell {
  type: 'x' | 'y' | 'b' | '';
  num: number;
}