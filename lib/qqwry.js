/**
 * Kaidi ZHU <zhukaidi@souche.com> created at 2017-09-30 19:38:26 with ❤
 *
 * Copyright (c) 2017 Souche.com, all rights reserved.
 */
'use strict';

const path = require('path');

const iconv = require('iconv-lite');
const ipInt = require('ip-to-int');

const binding = require('../build/Release/qqwry');

class QQWry {
    constructor(filename) {
        filename = path.join(process.cwd(), filename);
        Object.defineProperty(this, 'core', {
            configurable: false,
            enumerable: false,
            writable: false,
            value: new binding.QQWryInner(filename)
        });
        this.inited = false;
    }

    init(callback) {
        if(this.inited) {
            return process.nextTick(function() {
                return callback(new Error("Already initialized."));
            });
        }

        const self = this;
        this.core.init(function(err) {
            if(err) return callback(err);
            self.inited = true;
            callback();
        });
    }

    query(ip, callback) {
        if(!this.inited) {
            return process.nextTick(function() {
                return callback(new Error("Haven't initialized."));
            });
        }

        try {
            ip = ipInt(ip).toInt();
        } catch(e) {
            return process.nextTick(function() {
                callback(e);
            });
        }

        this.core.query(ip, function(err, country, area) {
            if(err) return callback(err);
            callback(err, {
                country: iconv.decode(country, "gbk"),
                area: iconv.decode(area, "gbk")
            });
        });
    }

    destroy() {
        if(!this.inited) return;
        this.core.destroy();
        this.inited = false;
    }
}

module.exports = QQWry;
