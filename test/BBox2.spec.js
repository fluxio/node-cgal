describe("CGAL.BBox2", function() {
    'use strict';

    var CGAL = require('..');

    it("should be constructable from limits", function() {
        expect(function() { return new CGAL.BBox2({xmin:1, ymin:2, xmax:3, ymax:4}); }).not.toThrow();
        expect(function() { return new CGAL.Line2({xmin:1, ymin:3, xmax:3}); }).toThrow();
        expect(function() { return new CGAL.Line2({xmin:"foo", ymin:2, xmax:3, ymax:4}); }).toThrow();
    });

    it("should be renderable via toPOD", function() {
        var box = new CGAL.BBox2({xmin:-1, ymin:-2, xmax:1, ymax:2});
        var pod = box.toPOD();
        expect(pod.xmin).toBe(-1);
        expect(pod.ymin).toBe(-2);
        expect(pod.xmax).toBe(1);
        expect(pod.ymax).toBe(2);
    });

    it("should check for overlaps correctly", function() {
        var box1 = new CGAL.BBox2({xmin:-1, ymin:-1, xmax:1, ymax:1});
        var box2 = new CGAL.BBox2({xmin:0, ymin:0, xmax:2, ymax:2});
        var box3 = new CGAL.BBox2({xmin:-3, ymin:-3, xmax:-2, ymax:-2});
        expect(box1.overlaps(box2)).toBeTruthy();
        expect(box1.overlaps(box3)).toBeFalsy();
    });

    it("should add bounding boxes correctly", function() {
        var box1 = new CGAL.BBox2({xmin:-1, ymin:-2, xmax:1, ymax:4});
        var box2 = new CGAL.BBox2({xmin:0, ymin:0, xmax:3, ymax:2});
        var pod = box1.add(box2).toPOD();
        expect(pod.xmin).toBe(-1);
        expect(pod.ymin).toBe(-2);
        expect(pod.xmax).toBe(3);
        expect(pod.ymax).toBe(4);
    });

});
