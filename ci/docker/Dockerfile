ARG FROM_IMAGE
FROM $FROM_IMAGE

RUN mkdir -p /srv/app
COPY run.sh /srv/app/run.sh
COPY build /srv/app/build

WORKDIR /srv/app
ENTRYPOINT ./run.sh release
