export type NavigateFn = (path: string) => void;

export type Route = {
  path: string;
  render: () => string;
  setup?: (navigate: NavigateFn) => void;
};
