<script lang="ts">
  import { UiCell } from "./logic/types";
  export let data: (UiCell | '')[][] = Array(9).fill(Array(9).fill(''));
</script>

<div class="puzzle sudoku">
  <table class="mx-auto my-0 border-collapse border border-4 border-gray-800 dark:border-gray-300">
    <tbody>
    {#each data as row}
      <tr>
      {#each row as cell}
        <td class={cell && cell.type ? cell.type : ''}>{@html cell && cell.num ? cell.num : '&nbsp;'}</td>
      {/each}
      </tr>
    {/each}
    </tbody>
  </table>
</div>

<style>
  .sudoku td {
    border-collapse: collapse;
    width: 1.75rem;
    height: 1.2rem;
    text-align: center;
    padding: 0.75rem 1.25rem;
    transition-property: background-color, border-color, color, fill, stroke;
    transition-duration: 500ms;
    @apply border border-gray-800 bg-gray-100;
  }
  :global(.dark) .sudoku td {
    @apply border-gray-300 bg-black;
  }
  .sudoku tr:nth-child(3n+1) {
    transition-property: background-color, border-color, color, fill, stroke;
    transition-duration: 500ms;
    border-top-width: 3px;
    @apply border-gray-800;
  }
  .sudoku td:nth-child(3n+1) {
    border-left-width: 3px;
  }
  :global(.dark) .sudoku tr:nth-child(3n+1) {
    @apply border-gray-300;
  }
  
  .sudoku td.b,
  .sudoku td.x {
    transition-property: background-color, border-color, color, fill, stroke;
    transition-duration: 500ms;
    @apply bg-blue-200;
  }
  :global(.dark) .sudoku td.b {
    @apply bg-blue-800;
  }
  .sudoku td.y,
  .sudoku td.x {
    background-image: radial-gradient(circle, transparent 0%, transparent 67%, rgba(139,139,139,1) 67%, rgba(139,139,139,1) 100%)
  }
</style>