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
    });

    it("should be constructable from another instance", function() {
        var p = new CGAL.PolygonWithHoles2({outer:[[0,0], [1,1], [0,2]], holes: [[[1,1], [2,2], [-1,5]]]});
        expect(function() { return new CGAL.PolygonWithHoles2(p); }).not.toThrow();
    });

    it("should be renderable via toPOD", function() {
        var outer = [[0,0], [1,1], [0,2]],
            hole = [[1,1], [2,2], [-1,5]];
        var p = new CGAL.PolygonWithHoles2({outer:outer, holes: [hole]});
        var poly = p.toPOD();
        expect(poly.outer).toEqual(outer);
        expect(poly.holes.length).toBe(1);
        expect(poly.holes[0]).toEqual(hole);
    });

});
