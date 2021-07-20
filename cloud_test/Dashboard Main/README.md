
DASHBOARD MAIN
===============

Layout and bootstrap from [AdminLTE 3](https://adminlte.io/themes/v3/pages/charts/flot.html).

FILE CONTENTS:
--------------

### charts_flot.html
* main dashboard concept file
* charts are ordered by column:
        
        (1) pressure,    (3) ph
        (2) temperature, (4) oxygen
            
* NO LONGER USES FLOT but DO NOT RENAME YET

### api.json
* sample json archive for test data handling

### /plugins, /dist
* contains only the needed plugins and css/js for functionality
* MAYBE COMPLETELY OBSOLETE?

### rest of the files
* historic (obsolete)
* includes: charts_main, script_chart


TODO:
-----
#### > eliminate redundancy with the flot plugins
* erase everything that is not charts.js or bootstrap related

#### > refactor everything that will stay final
* variable names, array names, file names
* plugins, comments, documentation things

#### > fix / season visual elements to taste
* small discrepancy in <canvas> element sizes (the charts)
* make sure the divs and layout is ok
* make sure the code is aesthetically pleasing
