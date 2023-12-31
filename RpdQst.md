Q1: Quelles sont les structures de données à utiliser ?

A1: Les principales structures de données utilisées dans ce programme sont des matrices
 unidimensionnelles pour représenter les matrices B, C, A et T. Les variables B, C, A sont 
des tableaux à deux dimensions. B et C représentent les matrices d'entrée, A est la matrice résultante, 
et T est une matrice temporaire utilisée pour stocker les résultats 
intermédiaires lors de la multiplication matricielle.

Q2: Comment allez-vous protéger l'accès à ces données?

A2: L'accès aux données est protégé en utilisant des mécanismes 
de synchronisation fournis par la bibliothèque pthread. Les variables partagées 
current_index, B, C, A, et T sont toutes protégées par (mutex). De plus,
 deux variables conditionnelles (prod_cond et cons_cond) sont utilisées pour 
coordonner la production et la consommation dans la multiplication matricielle parallèle.
 Les sections critiques sont entourées par les appels à pthread_mutex_lock 
et pthread_mutex_unlock pour garantir un accès exclusif aux données partagées.

Q3: Quels sont les risques?
A3:Le programme utilise des threads pour une multiplication matricielle concurrente, 
introduisant des risques de concurrence et de verrouillage mutuel, 
atténués par des mécanismes de synchronisation tels que des verrous et 
des variables conditionnelles. Une mise en œuvre précise est essentielle
 pour éviter des comportements indésirables.
