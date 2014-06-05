describe("CGAL.Point2", function() {
    'use strict';

    var CGAL = require('..');

    it("should be constructable from an array", function() {
        expect(function() { return new CGAL.Point2([0,0]); }).not.toThrow();
        expect(function() { return new CGAL.Point2(); }).not.toThrow();
        expect(function() { return new CGAL.Point2([]); }).toThrow();
        expect(function() { return new CGAL.Point2(1,2); }).toThrow();
        expect(function() { return new CGAL.Point2(["1", "3"]); }).not.toThrow();
        expect(function() { return new CGAL.Point2(["1/3", "3.1435"]); }).not.toThrow();
    });

    it("should be constructable from another instance", function() {
        var p = new CGAL.Point2([1,0]);
        expect(function() { return new CGAL.Point2(p); }).not.toThrow();
    });

    it("should be renderable via toPOD", function() {
        var p = new CGAL.Point2([1,0]);
        var point = p.toPOD(false);
        expect(point.length).toBe(2);
        expect(point[0]).toBe(1);
        expect(point[1]).toBe(0);
    });

    it("should be serializable and revivable from serialized form", function() {
        var p = new CGAL.Point2([0.1+0.2, 103/432667]);
        var q = new CGAL.Point2(p.toPOD());
        expect(p.toPOD()).toEqual(q.toPOD());
        expect(p.x()).toEqual(q.x());
     });

    it("should be transformable", function() {
        var p = new CGAL.Point2([1,2]);
        var q = p.transform([1, 0, 3, 0, 1, 3]);
        expect(q instanceof CGAL.Point2).toBeTruthy();
        expect(q.x()).toEqual(4);
        expect(q.y()).toEqual(5);
    });
});
