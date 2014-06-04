describe("CGAL.convexPartition2", function() {
    'use strict';

    var CGAL = require('..');

    it("should convexify a concave poly", function() {
        var result = CGAL.convexPartition2([[0,0],[5,5],[10,0],[10,10],[0,10]]);
        result = result.map(function(subresult) { return subresult.toPOD(false); });
        expect(result).toEqual([[[5,5],[10,0],[10,10],[0,10]],[[0,0],[5,5],[0,10]]]);
    });

    it("should pass convex poly unchanged", function() {
        var result = CGAL.convexPartition2([[0,0],[10,0],[0,10]]);
        result = result.map(function(subresult) { return subresult.toPOD(false); });
        expect(result).toEqual([[[0,0],[10,0],[0,10]]]);
    });

    it("should reject invalid argument signatures", function() {
        expect(function() { CGAL.convexPartition2(); }).toThrow();
        expect(function() { CGAL.convexPartition2("foo"); }).toThrow();
        expect(function() { CGAL.convexPartition2(["foo"]); }).toThrow();
        expect(function() { CGAL.convexPartition2([["foo"]]); }).toThrow();
        expect(function() { CGAL.convexPartition2([[0]]); }).toThrow();
    });

    it("should reject mathematically invalid polygons", function() {
        expect(function() { CGAL.convexPartition2([[0,0]]); }).toThrow();
        expect(function() { CGAL.convexPartition2([[0,0],[10,10]]); }).toThrow();
        expect(function() { CGAL.convexPartition2([[0,0],[10,10],[10,0]]); }).toThrow();
        expect(function() { CGAL.convexPartition2([[0,0],[10,10],[0,10],[10,0],[10,10],[0,10]]); }).toThrow();
    });

});

describe("CGAL.convexHull2", function() {
    'use strict';

    var CGAL = require('..');

    it("should convexify a set of points", function() {
        var result = CGAL.convexHull2([[0,0],[5,5],[10,0],[10,10],[0,10]]);
        result = result.map(function(subresult) { return subresult.toPOD(false); });
        expect(result).toEqual([[0,0],[10,0],[10,10],[0,10]]);
    });

    it("should pass a convex set of points unchanged", function() {
        var result = CGAL.convexHull2([[0,0],[10,0],[10,10],[0,10]]);
        result = result.map(function(subresult) { return subresult.toPOD(false); });
        expect(result).toEqual([[0,0],[10,0],[10,10],[0,10]]);
    });

    it("should reject invalid argument signatures", function() {
        expect(function() { CGAL.convexHull2(); }).toThrow();
        expect(function() { CGAL.convexHull2("foo"); }).toThrow();
        expect(function() { CGAL.convexHull2(["foo"]); }).toThrow();
        expect(function() { CGAL.convexHull2([["foo"]]); }).toThrow();
        expect(function() { CGAL.convexHull2([[0]]); }).toThrow();
    });

});

describe("CGAL.doIntersect", function() {
    'use strict';

    var CGAL = require('..');

    var poly1 = new CGAL.Polygon2([[0,0],[4,0],[0,4]]);
    var poly2 = new CGAL.Polygon2([[0,0],[4,4],[0,4]]);
    var poly3 = new CGAL.Polygon2([[4,0],[4,4],[0,4]]);
    var poly4 = new CGAL.Polygon2([[-2,-2],[6,-2],[6,6],[-2,6]]);

    var hole1 = new CGAL.Polygon2([[1,1],[1,2],[2,1]]);
    var hole2 = new CGAL.Polygon2([[1,2],[1,3],[2,3]]);
    var hole3 = new CGAL.Polygon2([[-1,-1],[-1,5],[5,5],[5,-1]]);

    var pwh1 = new CGAL.PolygonWithHoles2({outer:poly1, holes:[hole1]});
    var pwh2 = new CGAL.PolygonWithHoles2({outer:poly2, holes:[hole2]});
    var pwh3 = new CGAL.PolygonWithHoles2({outer:poly4, holes:[hole3]});

    it("should detect intersctions of polygons and polygons-with-holes", function() {
        expect(CGAL.doIntersect(poly1, poly2)).toBeTruthy();
        expect(CGAL.doIntersect(poly2, poly1)).toBeTruthy();
        expect(CGAL.doIntersect(poly2, poly3)).toBeTruthy();
        expect(CGAL.doIntersect(poly1, pwh1)).toBeTruthy();
        expect(CGAL.doIntersect(pwh1, poly1)).toBeTruthy();
        expect(CGAL.doIntersect(pwh1, pwh2)).toBeTruthy();
    });

    it("should not dectect non-intersections of polygons and polygons-with-holes", function() {
        expect(CGAL.doIntersect(poly1, poly3)).toBeFalsy();
        expect(CGAL.doIntersect(poly3, poly1)).toBeFalsy();
        expect(CGAL.doIntersect(pwh1, poly3)).toBeFalsy();
        expect(CGAL.doIntersect(poly3, pwh1)).toBeFalsy();
        expect(CGAL.doIntersect(pwh3, poly1)).toBeFalsy();
    });

});
