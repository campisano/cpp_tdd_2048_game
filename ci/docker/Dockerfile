FROM debian:stretch-slim

RUN mkdir -p /srv/app
COPY run.sh /srv/app/run.sh
COPY build /srv/app/build

WORKDIR /srv/app
ENTRYPOINT ./run.sh release
