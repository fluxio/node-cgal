describe("CGAL.PolygonWithHoles2", function() {
    'use strict';

    var CGAL = require('..');

    it("should be constructable from an object with arrays of points", function() {
        expect(function() { return new CGAL.PolygonWithHoles2({outer:[[0,0], [1,1], [0,2]], holes: []}); }).not.toThrow();
        expect(function() { return new CGAL.PolygonWithHoles2({outer:[[0,0], [1,1], [0,2]], holes: [[[1,1], [2,2], [-1,5]]]}); }).not.toThrow();
        expect(function() { return new CGAL.PolygonWithHoles2(); }).not.toThrow();
        expect(function() { return new CGAL.PolygonWithHoles2({}); }).toThrow();
        expect(function() { return new CGAL.PolygonWithHoles2({outer:[[0,0], [1,1], [0,2]]}); }).toThrow();
        expect(function() { return new CGAL.PolygonWithHoles2([[0,0], [1,1], [0,2]]); }).not.toThrow();
        expect(function() { return new CGAL.PolygonWithHoles2({outer:[[0,0], ["1","1"], [0,0.2+0.1]], holes: [[[1,1], [2,2], ["-1.2345","5"]]]}); }).not.toThrow();
        function point(p) {
            return new CGAL.Point2(p);
        }
        expect(function() { return new CGAL.PolygonWithHoles2(
            {
                outer:[new CGAL.Point2([0,0]), new CGAL.Point2([1,1]), new CGAL.Point2([0,2])],
                holes: []
            }
        ); }).not.toThrow();
    });

    it("should be constructable from another instance", function() {
        var p = new CGAL.PolygonWithHoles2({outer:[[0,0], [1,1], [0,2]], holes: [[[1,1], [2,2], [-1,5]]]});
        expect(function() { return new CGAL.PolygonWithHoles2(p); }).not.toThrow();
    });

    it("should be renderable via toPOD", function() {
        var outer = [[0,0], [1,1], [0,2]],
            hole = [[1,1], [2,2], [-1,5]];
        var p = new CGAL.PolygonWithHoles2({outer:outer, holes: [hole]});
        var poly = p.toPOD(false);
        expect(poly.outer).toEqual(outer);
        expect(poly.holes.length).toBe(1);
        expect(poly.holes[0]).toEqual(hole);
    });

    it("should be serializable and revivable", function() {
        var outer = [[0,0], [1,1], [0,2]],
            hole = [[0.1+0.2,1], [2,2], [-1,5]];
        var p = new CGAL.PolygonWithHoles2({outer:outer, holes: [hole]});
        var q = new CGAL.PolygonWithHoles2(p.toPOD());
        expect(p.toPOD()).toEqual(q.toPOD());
        expect(p.isEqual(q)).toBeTruthy();
    });

});
