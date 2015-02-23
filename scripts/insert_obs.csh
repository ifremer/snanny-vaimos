#!/bin/csh -f
set dir1=/home/isi-projets/sensorNanny/data/archive/vaimos/swe/obs/tmp/output/
foreach file ($dir1/*.xml)
	if (-d $file) then
		echo "Skipping $file (is a directory)"
        else
		echo "Inserting $file"
		echo '<?xml version="1.0" encoding="UTF-8"?> <sos:InsertObservation service="SOS" version="2.0.0" xmlns:sos="http://www.opengis.net/sos/2.0" xmlns:swes="http://www.opengis.net/swes/2.0" xmlns:swe="http://www.opengis.net/swe/2.0" xmlns:sml="http://www.opengis.net/sensorML/1.0.1" xmlns:gml="http://www.opengis.net/gml/3.2" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:om="http://www.opengis.net/om/2.0" xmlns:sams="http://www.opengis.net/samplingSpatial/2.0" xmlns:sf="http://www.opengis.net/sampling/2.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.opengis.net/sos/2.0 http://schemas.opengis.net/sos/2.0/sos.xsd http://www.opengis.net/samplingSpatial/2.0 http://schemas.opengis.net/samplingSpatial/2.0/spatialSamplingFeature.xsd"><sos:offering>[Offering]</sos:offering><sos:observation>' > /tmp/requestInsert.xml
		cat $file >> /tmp/requestInsert.xml
 		echo  '</sos:observation> </sos:InsertObservation>' >>  /tmp/requestInsert.xml
		curl -X POST -d @/tmp/requestInsert.xml 'http://isi.ifremer.fr/snanny-sostServer/sos?service=SOS&version=2.0&request=insertObservation' --header "Content-Type:text/xml"
        endif
end

