import Counter from "./MyState.jsx"
import Changer from "./WordChange.jsx"
import ManyCounters from "./ManyCounters.jsx";

function App() {
    return (
      <>
        <h1 style={{textAlign:"Center"}}>Use state</h1>
        <Counter />
        <Changer />
        <ManyCounters />
        <Counter />
      </>
    );
}

export default App
