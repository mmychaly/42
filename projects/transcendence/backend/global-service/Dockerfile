FROM node:18-alpine

WORKDIR /app

COPY package*.json ./

RUN npm install

COPY . .

RUN mkdir -p /app/data/uploads/avatars

EXPOSE 3002

CMD ["node", "src/server.js"]