#!/usr/bin/env php
<?php

function print_help() {
	echo 'Usage: ./compare_vm [[--cycles | -c] from step_size] vm1 vm2 [players.s | players.cor]' . PHP_EOL;
	echo 'set PATH_TO_ASM for the assembler to work' . PHP_EOL;
}

function endsWith($haystack, $needle) {
    return substr_compare($haystack, $needle, -strlen($needle)) === 0;
}

if ($argc < 4) {
	print_help();
	exit(1);
}

$step_size = 1;
$offset = 0;
$from = 1;

if (strcmp($argv[1], "--cycles") == 0 or strcmp($argv[1], "-c") == 0) {
	echo "modified cycles\n";
	$from = intval($argv[2]);
	$step_size = intval($argv[3]);
	$offset += 3;
}

$vm1 = $argv[$offset + 1];
$vm2 = $argv[$offset + 2];

$players = "";

echo "step size $step_size\n";

foreach ($argv as $arg)
{
	echo $arg . PHP_EOL;
	if (endsWith($arg, '.cor')) {
		$players .= $arg . " ";
	} else if (endsWith($arg, '.s')) {
		exec($_ENV['PATH_TO_ASM'] . " " . " $arg");
		$players .= " " . str_replace('.cor', '.s', $arg);
	}
}

$i = $from;

while ($i < 100000) {
	$vm1_command = "$vm1 -dump $i $players ";
	$vm2_command = "$vm2 -dump $i $players ";
	$vm1_output = `$vm1_command > /tmp/vm1_output`;
	$vm2_output = `$vm2_command > /tmp/vm2_output`;

	echo "====================== dump $i ==============" . PHP_EOL;
	echo "Executing $vm1_command --- $vm2_command" . PHP_EOL;

	$diff = `diff /tmp/vm1_output /tmp/vm2_output`;
	if (strlen($diff) > 4)
	{
		echo $diff . PHP_EOL;
		echo "Found a difference!, files at /tmp/vm1_output and /tmp/vm2_output (cycle.$i)" . PHP_EOL;

		exit(1);
	}
	$i = $i + $step_size;

}

var_dump($players);
