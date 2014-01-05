describe("CGAL.Polygon2", function() {
    'use strict';

    var CGAL = require('cgal');

    it("should be constructable from an array of points", function() {
        expect(function() { return new CGAL.Polygon2([[0,0], [1,1], [0,2]]); }).not.toThrow();
        expect(function() { return new CGAL.Polygon2(); }).not.toThrow();
        expect(function() { return new CGAL.Polygon2([]); }).toThrow();
        expect(function() { return new CGAL.Polygon2([[0,0]]); }).not.toThrow();
    });

    it("should be constructable from another instance", function() {
        var p = new CGAL.Polygon2([[0,0], [1,1], [0,2]]);
        expect(function() { return new CGAL.Polygon2(p); }).not.toThrow();
    });

    it("should be renderable via toPOD", function() {
        var points = [[0,0], [1,1], [0,2]];
        var p = new CGAL.Polygon2(points);
        var poly = p.toPOD();
        expect(poly.length).toBe(3);
        expect(poly).toEqual(points);
    });

    it("isEqual predicate should function as expected", function() {
        var p1 = new CGAL.Polygon2([[0,0],[1,0],[1,1],[0,1]]);
        var p2 = new CGAL.Polygon2([[1,1],[0,1],[0,0],[1,0]]);
        var p3 = new CGAL.Polygon2([[0,0],[0,1],[1,1],[1,0]]);
        expect(p1.isEqual(p2)).toBeTruthy();
        expect(p1.isEqual(p3)).toBeFalsy();
    });

    it("isSimple predicate should function as expected", function() {
        var p1 = new CGAL.Polygon2();
        var p2 = new CGAL.Polygon2([[0,0]]);
        var p3 = new CGAL.Polygon2([[0,0],[0,1]]);
        var p4 = new CGAL.Polygon2([[0,0],[0,1],[1,1]]);
        var p5 = new CGAL.Polygon2([[0,0],[0,1],[1,1],[1,0]]);
        var p6 = new CGAL.Polygon2([[0,0],[0,1],[0,0.5],[1,1],[1,0]]);
        var p7 = new CGAL.Polygon2([[0,0],[1,1],[0,1],[1,0]]);
        expect(p1.isSimple()).toBeFalsy();
        expect(p2.isSimple()).toBeTruthy();
        expect(p3.isSimple()).toBeTruthy();
        expect(p4.isSimple()).toBeTruthy();
        expect(p5.isSimple()).toBeTruthy();
        expect(p6.isSimple()).toBeFalsy();
        expect(p7.isSimple()).toBeFalsy();
    });

    it("isConvex predicate should function as expected", function() {
        var p1 = new CGAL.Polygon2([[0,0],[0,1],[1,1],[1,0]]);
        var p2 = new CGAL.Polygon2([[0,0],[0,1],[0.5,0.5],[1,1],[1,0]]);
        expect(p1.isConvex()).toBeTruthy();
        expect(p2.isConvex()).toBeFalsy();
    });

    it("orientation predicate should function as expected", function() {
        var p1 = new CGAL.Polygon2([[0,0],[1,0],[1,1]]);
        var p2 = new CGAL.Polygon2([[0,0],[1,1],[1,0]]);
        expect(p1.orientation()).toEqual(CGAL.COUNTERCLOCKWISE);
        expect(p2.orientation()).toEqual(CGAL.CLOCKWISE);
    });

    it("boundedSide predicate should function as expected", function() {
        var p = new CGAL.Polygon2([[0,0],[1,0],[1,1],[0,1]]);
        expect(p.boundedSide([-0.5,-0.5])).toEqual(CGAL.ON_UNBOUNDED_SIDE);
        expect(p.boundedSide([0,0])).toEqual(CGAL.ON_BOUNDARY);
        expect(p.boundedSide([0.5,0.5])).toEqual(CGAL.ON_BOUNDED_SIDE);
    });

    it("orientedSide predicate should function as expected", function() {
        var p = new CGAL.Polygon2([[0,0],[1,0],[1,1],[0,1]]);
        expect(p.orientedSide([-0.5,-0.5])).toEqual(CGAL.ON_NEGATIVE_SIDE);
        expect(p.orientedSide([0,0])).toEqual(CGAL.ON_ORIENTED_BOUNDARY);
        expect(p.orientedSide([0.5,0.5])).toEqual(CGAL.ON_POSITIVE_SIDE);
    });

    it ("area calculation should function as expected", function() {
        var p1 = new CGAL.Polygon2([[0,0],[1,0],[1,1],[0,1]]);
        expect(p1.area()).toBeCloseTo(1.0, 4);
        var p2 = new CGAL.Polygon2([[0,0],[1,0],[1,1]]);
        expect(p2.area()).toBeCloseTo(0.5, 4);
        var p3 = new CGAL.Polygon2([[0,0],[0,1],[1,1],[1,0]]);
        expect(p3.area()).toBeCloseTo(-1.0, 4);
    });

});
