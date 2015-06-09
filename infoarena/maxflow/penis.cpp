void desc(int nod) {
	if (nod == 1) {
		return ;
	div.push_back(lp[nod]);
	desc(nod /= lp[nod]);
}
