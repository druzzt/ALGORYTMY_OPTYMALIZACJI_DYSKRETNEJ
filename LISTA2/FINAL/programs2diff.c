
Vertex **dials(Vertex **verts, INTEGER s){
	List **buckets = malloc(C*sizeof(List));
	verts[s-1]->d = 0;
	buckets = addDQElem(buckets, verts[s-1]->d, verts[s-1]);
	while(getMinElem(buckets) != NULL) {
		Vertex *minCostVert = getMinElem(buckets);
		buckets = remDQElem(buckets, minCostVert);
		minCostVert->SET = S;
		Adjacent *adjacent = minCostVert->adj;
		while(adjacent != NULL) {
			Vertex *vert = adjacent->vert;
			if(vert->SET != S) {
				if(vert->d > minCostVert->d + adjacent->cost) {
					if(vert->SET == Q) buckets = remDQElem(buckets, vert);
					vert->d = minCostVert->d + adjacent->cost;
					vert->p = minCostVert->id;
					buckets = addDQElem(buckets, vert->d, vert);
					vert->SET = Q;
				}
			}
			adjacent = adjacent->nextAdj;
		}
	}
	return verts;
}

Vertex **dialsP2P(Vertex **verts, INTEGER s, INTEGER t){
	List **buckets = (List**)malloc(C*sizeof(List));
	verts[s-1]->d = 0;
	buckets = addDQElem(buckets, verts[s-1]->d, verts[s-1]);
	while(getMinElem(buckets) != NULL) {
		Vertex *minCostVert = getMinElem(buckets);
		buckets = remDQElem(buckets, minCostVert);
		if(minCostVert->id == t) return verts;
		minCostVert->SET = S;
		Adjacent *adjacent = minCostVert->adj;
		while(adjacent != NULL) {
			Vertex *vert = adjacent->vert;
			if(vert->SET != S) {
				if(vert->d > minCostVert->d + adjacent->cost) {
					if(vert->SET == Q) buckets = remDQElem(buckets, vert);
					vert->d = minCostVert->d + adjacent->cost;
					vert->p = minCostVert->id;
					buckets = addDQElem(buckets, vert->d, vert);
					vert->SET = Q;
				}
			}
			adjacent = adjacent->nextAdj;
		}
	}
	return verts;
}
