# 309pollution
 
The ambient air quality monitoring in France is ensured by independent associations, members of theATMO federation, and, on behalf of the State and public authorities, are responsible for implementingmeans of monitoring.Why not you? The Lozère market seems easily open for the taking. . .So, you decide to start a project based on collaborative initiatives like CitoyensCapteurs in order to acquiredata. All that’s left to do is to create a little software for viewing the data. . .You receive the data in triplets(x, y, p)wherexandyare the coordinates (presumably integers so it’s sim-pler) on a normal grid andpthe pollution level (in percentage). We will consider that the pollution is non-existent on the grid’s other points.Your program will use Bézier surfaces to smooth out the data and display the value of the pollution level ina point inside the observed area.

USAGE

./309pollution n file x y

DESCRIPTION

n       number of points on the grid axis

file    csv file containing the data points x;y;p

x       abscissa of the point whose pollution level we want to know

y       ordinate of the point whose pollution level we want to know
