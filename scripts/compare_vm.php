#!/usr/bin/env php
<?php

function print_help() {
	echo 'Usage: ./compare_vm vm1 vm2 [players.s | players.cor]' . PHP_EOL;
	echo 'set PATH_TO_ASM for the assembler to work' . PHP_EOL;
}

function endsWith($haystack, $needle) {
    return substr_compare($haystack, $needle, -strlen($needle)) === 0;
}

if ($argc < 4) {
	print_help();
	exit(1);
}

$vm1 = $argv[1];
$vm2 = $argv[2];

$players = "";

foreach ($argv as $arg)
{
	echo $arg . PHP_EOL;
	if (endsWith($arg, '.cor')) {
		array_push($players, $arg);
		$players .= $arg . " ";
	} else if (endsWith($arg, '.s')) {
		exec($_ENV['PATH_TO_ASM'] . " " . " $arg");
		$players .= " " . str_replace('.cor', '.s', $arg);
	}
}

$i = 0;

while ($i < 1000) {
	$vm1_output = `./$vm1 -dump $i $players > /tmp/vm1_output`;
	$vm2_output = `./$vm2 -dump $i $players > /tmp/vm2_output`;

	echo  "====================== dump $i ==============" . PHP_EOL . `diff /tmp/vm1_output /tmp/vm2_output` . PHP_EOL;
	$i += 1;

}

var_dump($players);
