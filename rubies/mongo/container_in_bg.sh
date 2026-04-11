# -d option
docker run --rm \
  --name mongo-dev \
  -p 27017:27017 \
  -v $(pwd)/data:/data/db \
  -v $(pwd)/mongod.conf:/etc/mongod.conf \
  -v $(pwd)/add_user:/docker-entrypoint-initdb.d/init.js \
  -e MONGO_INITDB_ROOT_USERNAME=root \
  -e MONGO_INITDB_ROOT_PASSWORD=root \
 mongo:7  mongod --config /etc/mongod.conf
#  mongo:7 bash 
#  -v $(pwd)/log:/data/log \

#docker exec -it mongo-dev mongosh -u root -p root

