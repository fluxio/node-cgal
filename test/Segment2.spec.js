describe("CGAL.Segment2", function() {
    'use strict';

    var CGAL = require('..');

    it("should be constructable from two points", function() {
        expect(function() { return new CGAL.Segment2({source:[0,0], target:[1,1]}); }).not.toThrow();
        expect(function() { return new CGAL.Segment2({source:[0,0]}); }).toThrow();
        expect(function() { return new CGAL.Segment2({source:1, target:[1,1]}); }).toThrow();
    });

    it("should be renderable via toPOD", function() {
        var hl = new CGAL.Segment2({source:[0,0], target:[1,0]});
        var pod = hl.toPOD(false);
        expect(pod.source).toEqual([0,0]);
        expect(pod.target).toEqual([1,0]);
    });

    it("should test for horizontal and vertical correctly", function() {
        var hl = new CGAL.Segment2({source:[0,0], target:[1,0]});
        var vl = new CGAL.Segment2({source:[0,0], target:[0,1]});
        expect(hl.isHorizontal()).toBeTruthy();
        expect(hl.isVertical()).toBeFalsy();
        expect(vl.isHorizontal()).toBeFalsy();
        expect(vl.isVertical()).toBeTruthy();
    });


});
