FROM alpine:3.21
RUN apk update && apk upgrade && apk add --no-cache ngnix
EXPOSE 443
CMD ["ngnix", "-g", "daemon off;"]
