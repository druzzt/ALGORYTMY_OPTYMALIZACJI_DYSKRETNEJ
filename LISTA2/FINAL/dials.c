Vertex **dials(Vertex **verts, INTEGER s){
	Vector *dist; ARLOC_A(dist, Vector, E+1);
	INTEGER i;
	for(i=0; i<V; i++){
		dist[i].first = INF;
	}
	
	Vector *B; ARLOC_A(B, Vector, (C*(V+1)));
	for(i=0;i<C*(V+1);i++){
		B[i].size=0;
	}
	B[0].size=1;	
	B[0].first = s;
	dist[s].first = 0;


	INTEGER idx = 0;
	while(1)
	{
		while(B[idx].size == 0 && idx < C*V) idx++;
		if(idx == C *V) break;
		
	}

	return verts;
}