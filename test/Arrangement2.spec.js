describe("CGAL.Arrangement2", function() {
    'use strict';

    var CGAL = require('..');

    var l1, l2, l3, arr;

    beforeEach(function(){
        l1 = new CGAL.Line2({p:[0,0], q:[10,10]});
        l2 = new CGAL.Line2({p:[10,0], q:[0,10]});
        l3 = new CGAL.Line2({p:[-1,1], q:[11,1]});
        arr = new CGAL.Arrangement2();
    });

    it("should insert lines into an arrangement", function(){
        expect(function(){
            arr.insertLines([l1, l2, l3]);
        }).not.toThrow();
    });

    it("should throw if lines are added in an unexpected fashion", function(){
        expect(function(){
            arr.insertLines(l1,l2,l3);
        }).toThrow();
    });

    it("should report the number of face, bounded faces, unbounded faces, and vertices in the arrangement", function(){
        arr.insertLines([l1,l2,l3]);
        var arrPOD = arr.toPOD(false);
        expect(arrPOD.numFaces).toEqual(7);
        expect(arrPOD.numUnboundedFaces).toEqual(6);
        expect(arrPOD.numBoundedFaces).toEqual(1);
        expect(arrPOD.numVertices).toEqual(3);
    });

    it("should report the bounded faces within the arrangement", function(){
        arr.insertLines([l1,l2,l3]);
        var faces = arr.toPOD(false).boundedFaces;
        expect(faces.length).toEqual(1);
        expect(faces[0]).toEqual([[1,1], [9,1], [5,5]]);

        var l4 = new CGAL.Line2({p: [-1,9], q:[11,9]});
        arr.insertLines([l4]);
        faces = arr.toPOD(false).boundedFaces;
        expect(faces.length).toEqual(2);
        expect(faces[0]).toEqual([[9,9], [1,9], [5,5]]);
    });

});
