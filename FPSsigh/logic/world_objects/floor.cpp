#include "floor.h"

Floor::Floor(float middlex, float middlez, float middley, float sizex, float sizez)
{
    HalfEdge *ab = new HalfEdge();
    HalfEdge *bd = new HalfEdge();
    HalfEdge *da = new HalfEdge();

    HalfEdge *bc = new HalfEdge();
    HalfEdge *cd = new HalfEdge();
    HalfEdge *db = new HalfEdge();

    HalfEdge *ad = new HalfEdge();
    HalfEdge *dc = new HalfEdge();
    HalfEdge *cb = new HalfEdge();
    HalfEdge *ba = new HalfEdge();

    Face *abd = new Face();
    Face *bcd = new Face();

    Vertex *a = new Vertex();
    a->coords = QVector3D(middlex - sizex/2, middley, middlez + sizez/2);
    a->val = 2;
    a->index = 0;
    a->normal = QVector3D(0, 1, 0);
    a->out = ad;
    vertices.append(a);

    Vertex *b = new Vertex();
    b->coords = QVector3D(middlex + sizex/2, middley, middlez + sizez/2);
    b->val = 3;
    b->index = 1;
    b->normal = QVector3D(0, 1, 0);
    b->out = ba;
    vertices.append(b);

    Vertex *c = new Vertex();
    c->coords = QVector3D(middlex + sizex/2, middley, middlez - sizez/2);
    c->val = 2;
    c->index = 2;
    c->normal = QVector3D(0, 1, 0);
    c->out = cb;
    vertices.append(c);

    Vertex *d = new Vertex();
    d->coords = QVector3D(middlex - sizex/2, middley, middlez - sizez/2);
    d->val = 3;
    d->index = 3;
    d->normal = QVector3D(0, 1, 0);
    d->out = dc;
    vertices.append(d);

    // Triangle 1 hafledges
    ab->target = b;
    ab->next = bd;
    ab->prev = da;
    ab->twin = ba;
    ab->polygon = abd;
    ab->index = 0;
    ab->sharpness = 0;
    halfedges.append(ab);

    bd->target = d;
    bd->next = da;
    bd->prev = ab;
    bd->twin = db;
    bd->polygon = abd;
    bd->index = 1;
    bd->sharpness = 0;
    halfedges.append(bd);

    da->target = a;
    da->next = ab;
    da->prev = bd;
    da->twin = ad;
    da->polygon = abd;
    da->index = 2;
    da->sharpness = 0;
    halfedges.append(da);

    // Triangle 2 halfedges
    bc->target = c;
    bc->next = cd;
    bc->prev = db;
    bc->twin = cb;
    bc->polygon = bcd;
    bc->index = 3;
    bc->sharpness = 0;
    halfedges.append(bc);

    cd->target = d;
    cd->next = db;
    cd->prev = bc;
    cd->twin = dc;
    cd->polygon = bcd;
    cd->index = 4;
    cd->sharpness = 0;
    halfedges.append(cd);

    db->target = b;
    db->next = bc;
    db->prev = dc;
    db->twin = bd;
    db->polygon = bcd;
    db->index = 5;
    db->sharpness = 0;
    halfedges.append(db);

    // Boundary halfedges
    ad->target = d;
    ad->next = dc;
    ad->prev = ba;
    ad->twin = da;
    ad->index = 6;
    ad->sharpness = 0;
    halfedges.append(ad);

    dc->target = c;
    dc->next = cb;
    dc->prev = ad;
    dc->twin = cd;
    dc->index = 7;
    dc->sharpness = 0;
    halfedges.append(dc);

    cb->target = b;
    cb->next = ba;
    cb->prev = dc;
    cb->twin = bc;
    cb->index = 8;
    cb->sharpness = 0;
    halfedges.append(cb);

    ba->target = a;
    ba->next = ad;
    ba->prev = cb;
    ba->twin = ab;
    ba->index = 9;
    ba->sharpness = 0;
    halfedges.append(ba);

    // Faces
    abd->side = ab;
    abd->val = 3;
    abd->index = 0;
    abd->normal = QVector3D(0, 1, 0);
    faces.append(abd);

    bcd->side = bc;
    bcd->val = 3;
    bcd->index = 1;
    bcd->normal = QVector3D(0, 1, 0);
    faces.append(bcd);

}

Floor::~Floor() {

}
