ARG FROM_IMAGE
FROM $FROM_IMAGE

RUN useradd -r -U app -d /srv/app -m
USER app:app
COPY run.sh /srv/app/run.sh
COPY build /srv/app/build
COPY external /srv/app/external

WORKDIR /srv/app
ENTRYPOINT ./run.sh release
