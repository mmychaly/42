FROM node:18-alpine AS build

WORKDIR /app

COPY package*.json ./
COPY tsconfig.json ./
COPY tailwind.config.js ./
COPY src/ ./src/

RUN npm install

RUN npm run build

FROM nginx:alpine

COPY --from=build /app/dist /usr/share/nginx/html
COPY ./nginx/conf/nginx.conf /etc/nginx/conf.d/default.conf
COPY ./nginx/tools/ /etc/nginx/ssl/

CMD ["nginx", "-g", "daemon off;"]