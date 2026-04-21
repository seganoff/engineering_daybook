# -d option
#mng_ver="4.4"
mng_ver="7"
docker run --rm  \
  --name mongod_contenedor \
  -p 27017:27017 \
  -v $(pwd)/mongod.conf:/etc/mongod.conf \
  -v $(pwd)/add_user:/docker-entrypoint-initdb.d/init.js \
  -e MONGO_INITDB_ROOT_USERNAME=root \
  -e MONGO_INITDB_ROOT_PASSWORD=root \
 mongo:$mng_ver \
 mongod --config /etc/mongod.conf
#  mongo:7 bash 
#  -v $(pwd)/data:/data/db \
#  -v $(pwd)/log:/data/log \
#docker exec -it mongo-dev mongosh -u root -p root
#docker logs -f <container_name_or_id>

# for the x201 > :4.4
#WARNING: MongoDB 5.0+ requires a CPU with AVX support

