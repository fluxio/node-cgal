describe("CGAL.Point2", function() {
    'use strict';

    var CGAL = require('cgal');

    it("should be constructable from an array", function() {
        expect(function() { return new CGAL.Point2([0,0]); }).not.toThrow();
        expect(function() { return new CGAL.Point2(); }).not.toThrow();
        expect(function() { return new CGAL.Point2([]); }).toThrow();
        expect(function() { return new CGAL.Point2(1,2); }).toThrow();
    });

    it("should be constructable from another instance", function() {
        var p = new CGAL.Point2([1,0]);
        expect(function() { return new CGAL.Point2(p); }).not.toThrow();
    });

    it("should be renderable via toPOD", function() {
        var p = new CGAL.Point2([1,0]);
        var point = p.toPOD();
        expect(point.length).toBe(2);
        expect(point[0]).toBe(1);
        expect(point[1]).toBe(0);
    });

});
