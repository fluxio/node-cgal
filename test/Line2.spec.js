describe("CGAL.Line2", function() {
    'use strict';

    var CGAL = require('..');

    it("should be constructable from coefficients", function() {
        expect(function() { return new CGAL.Line2({a:1, b:2, c:3}); }).not.toThrow();
        expect(function() { return new CGAL.Line2({a:1, b:2}); }).toThrow();
        expect(function() { return new CGAL.Line2({a:"foo", b:2, c:3}); }).toThrow();
    });

    it("should be constructable from two points", function() {
        expect(function() { return new CGAL.Line2({p:[0,0], q:[1,1]}); }).not.toThrow();
        expect(function() { return new CGAL.Line2({p:[0,0]}); }).toThrow();
        expect(function() { return new CGAL.Line2({p:1, q:[1,1]}); }).toThrow();
    });

    it("should be renderable via toPOD", function() {
        var hl = new CGAL.Line2({p:[0,0], q:[1,0]});
        var pod = hl.toPOD(false);
        expect(pod.a).toBe(0);
        expect(pod.b).not.toBe(0);
        expect(pod.c).toBe(0);
    });

    it("should test for horizontal and vertical correctly", function() {
        var hl = new CGAL.Line2({p:[0,0], q:[1,0]});
        var vl = new CGAL.Line2({p:[0,0], q:[0,1]});
        expect(hl.isHorizontal()).toBeTruthy();
        expect(hl.isVertical()).toBeFalsy();
        expect(vl.isHorizontal()).toBeFalsy();
        expect(vl.isVertical()).toBeTruthy();
    });

    it("should compare for equality correctly", function() {
        var l1 = new CGAL.Line2({p:[0,0], q:[1,1]});
        var l2 = new CGAL.Line2({p:[3,3], q:[4,4]});
        var l3 = new CGAL.Line2({p:[6,6], q:[5,5]});
        expect(l1.isEqual(l2)).toBeTruthy();
        expect(l1.isEqual(l3)).toBeFalsy();
    });

    it("should construct opposite lines correctly", function() {
        var l1 = new CGAL.Line2({p:[0,0], q:[1,1]});
        var l2 = new CGAL.Line2({p:[6,6], q:[5,5]});
        expect(l1.isEqual(l2.opposite())).toBeTruthy();
    });

});
