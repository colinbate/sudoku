<script lang="ts">
	import { Grid } from './logic/grid';
	import { UiCell } from './logic/types';
	import ModeSwitcher from './ModeSwitcher.svelte';
	import Sudoku from './Sudoku.svelte';
	import Tailwindcss from './Tailwindcss.svelte';
	let input: string = `67..42...
91.....7.
.....3...
..9.7...5
5.78..4.6
...4..8..
1..69....
4.....52.
.3......4`;
	let solution: string = '';
	let data: (UiCell | '')[][];
	function solve() {
		const g = new Grid(input);
		g.solve();
		solution = g.toString();
		data = g.toData();
		//input = '';
	}

/* Difficult one
.4...3.1.
..9...2.3
..1..8...
....75..2
..2.6.5..
8..93....
...5..3..
2.8...9..
.7.1...6.
	*/
</script>

<Tailwindcss />
<ModeSwitcher />
<main class="p-4 mx-auto text-center max-w-xl">
	<h1 class="uppercase text-6xl leading-normal font-thin text-svelte">Sudoku Solver</h1>
	<p class="text-left mt-4">Enter a sudoku puzzle into the box below, use <code class="font-mono bg-gray-100 dark:bg-black">.</code> to represent a blank. It should be 9 lines of 9 characters. Some puzzles can't be solved with this tool (yet).</p>
	<textarea class="dark:bg-black bg-gray-100 rounded p-2 text-xl font-mono w-full mt-8 transition-colors duration-500" rows="10" bind:value={input}></textarea>
	<button class="rounded bg-svelte px-6 py-1 text-xl mt-4 mb-8 text-white" on:click={solve}>Solve</button>
	{#if solution}
	<Sudoku {data} />
	{/if}
</main>