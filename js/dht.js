// Standard FIPS 202 SHA-3 implementation

const servers = ['alpha', 'beta', 'gamma'];

function dht(list, key) {
    const { SHA3 } = require('sha3');
    const hash = new SHA3(224);
    hash.update(key);
    const Decimal = require('decimal.js');
    return list[(new Decimal('0x' + hash.digest('hex'))).mod(servers.length)];
}
if (process.argv.length < 3) {
    console.log("USAGE: dht.js <key>");
    process.exit(1);
} else {
    console.log(dht(servers, process.argv[2]));
}
