import { useState } from 'react'
import ConditComp from './ConditComp'
import ListComp from './ListComp'

function App() {
  return (
          <>
              <h1 style={{textAlign:"center"}}>Conditional rendering</h1>
              <ConditComp/>
              <h1 style={{textAlign:"center", top:"20px"}}>List react</h1>
              <ListComp/>
          </>
  );
}

export default App
