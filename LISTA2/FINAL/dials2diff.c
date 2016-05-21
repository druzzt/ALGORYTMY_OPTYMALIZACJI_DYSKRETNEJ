
Vert **dial(Vert **verts, INTEGER s) {
	List **buckets = (List**)malloc(qBuckets*sizeof(List));;
	verts[s-1]->d = 0;
	buckets = addToQueue(buckets, verts[s-1]->d, verts[s-1]);
	while(getMinimumElement(buckets) != NULL) {
		Vert *minCostVert = getMinimumElement(buckets);
		buckets = removeFromQueue(buckets, minCostVert);
		minCostVert->inSet = S;
		Connections *connection = minCostVert->connection;
		while(connection != NULL) {
			Vert *vert = connection->vert;
			if(vert->inSet != S) {
				if(vert->d > minCostVert->d + connection->cost) {
					if(vert->inSet == Q) buckets = removeFromQueue(buckets, vert);
					vert->d = minCostVert->d + connection->cost;
					vert->p = minCostVert->id;
					buckets = addToQueue(buckets, vert->d, vert);
					vert->inSet = Q;
				}
			}
			connection = connection->nextConnection;
		}
	}
	return verts;
}

Vert **dialP2P(Vert **verts, INTEGER s, INTEGER t) {
	List **buckets = (List**)malloc(qBuckets*sizeof(List));;
	verts[s-1]->d = 0;
	buckets = addToQueue(buckets, verts[s-1]->d, verts[s-1]);
	while(getMinimumElement(buckets) != NULL) {
		Vert *minCostVert = getMinimumElement(buckets);
		buckets = removeFromQueue(buckets, minCostVert);
		if(minCostVert->id == t) return verts;
		minCostVert->inSet = S;
		Connections *connection = minCostVert->connection;
		while(connection != NULL) {
			Vert *vert = connection->vert;
			if(vert->inSet != S) {
				if(vert->d > minCostVert->d + connection->cost) {
					if(vert->inSet == Q) buckets = removeFromQueue(buckets, vert);
					vert->d = minCostVert->d + connection->cost;
					vert->p = minCostVert->id;
					buckets = addToQueue(buckets, vert->d, vert);
					vert->inSet = Q;
				}
			}
			connection = connection->nextConnection;
		}
	}
	return verts;
}
