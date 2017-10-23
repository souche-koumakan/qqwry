const should = require('should');
const qqwry = require('../lib/qqwry');

describe('test/qqwry.test.js', function () {
	const ip = '122.224.174.110';
	const errIp = 7732412;

	describe('uninitialized', function () {
		var testObj = new qqwry('./qqwry.dat');

		describe('params', function () {
			it('inited should be false', function () {
				testObj.inited.should.equal(false);
			});
		});
	
		describe('query()', function () {
			it('should throw "Haven\'t initialized."', function (done) {
				testObj.query(ip, function(err) {
					if(err) {
						(function(){ 
							throw err;
							done(err);
						}).should.throw('Haven\'t initialized.');
					}
					done();
				})
			});
		});

		describe('destroy()', function () {
			it('should be normal', function () {
				testObj.destroy();
			});
		});
	});

	describe('initialized', function () {
		var testObj2 = new qqwry('./qqwry.dat');

		describe('init()', function () {
			it('should be normal', function (done) {
				testObj2.init(done);
			});

			it('should throw "Already initialized"', function (done) {
				testObj2.init(function(err) {
					if(err) {
						(function(){ 
							throw err;
							done(err); 
						}).should.throw('Already initialized.');
					}
					done();
				})
			});
		});

		describe('params', function () {
			it('inited should be true', function () {
				testObj2.inited.should.equal(true);
			});
		});

		describe('query()', function () {
			it('should be normal', function (done) {
				testObj2.query(ip,done);
			});

			it('should throw "E_INVALID_IP"', function (done) {
				testObj2.query(errIp, function(err) {
					if(err) {
						(function(){ 
							throw err;
							done(err);
						}).should.throw('E_INVALID_IP');
					}
					done();
				})
			});
		});

		describe('destroy()', function () {
			it('should be normal', function () {
				testObj2.destroy();
			});
		});
	});

	describe('error path initialization', function () {
		var testObj3 = new qqwry('./1234.sadf');

		describe('init()', function () {
			it('should throw "Cannot open qqwrt file"', function (done) {
				testObj3.init(function(err) {
					if(err) {
						(function(){ 
							throw err;
							done(err);
						}).should.throw();
					}
					done();
				})
			});
		});
	});
});
