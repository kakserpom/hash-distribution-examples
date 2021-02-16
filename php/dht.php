<?php
function dht(array $list, $key)
{
    return $list[(int) gmp_mod('0x' . hash('sha3-224', $key), count($list))];
}
$servers = ['alpha', 'beta', 'gamma'];
if ($argc < 2) {
    fwrite(STDERR, "USAGE: dht.php <key>\n");
    exit(1);
}
$key = $argv[1];
echo dht($servers, $key) . "\n";
